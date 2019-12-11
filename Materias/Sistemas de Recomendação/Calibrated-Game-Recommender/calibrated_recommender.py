import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

def compute_genre_distr(items):
    """Compute the genre distribution for a given list of Items."""
    distr = {}
    for item in items:
        for genre, score in item.genres.items():
            genre_score = distr.get(genre, 0.)
            distr[genre] = genre_score + score

    # we normalize the summed up probability so it sums up to 1
    # and round it to three decimal places, adding more precision
    # doesn't add much value and clutters the output
    for item, genre_score in distr.items():
        normed_genre_score = round(genre_score / len(items), 3)
        distr[item] = normed_genre_score

    return distr

def precision(user_item, user_id, reco_items, index2item):
    indptr = user_item.indptr
    indices = user_item.indices

    reco_ids = {item.id for item in reco_items}
    likes = {index2item[indices[i]] for i in range(indptr[user_id], indptr[user_id + 1])}

    relevant = len(reco_ids & likes)
    total = min(len(reco_items), len(likes))
    # cuidado com divisão por zero
    return relevant / total


def compute_kl_divergence(interacted_distr, reco_distr, alpha=0.01):
    """
    KL (p || q), the lower the better.

    alpha is not really a tuning parameter, it's just there to make the
    computation more numerically stable.
    """
    kl_div = 0.
    for genre, score in interacted_distr.items():
        reco_score = reco_distr.get(genre, 0.)
        reco_score = (1 - alpha) * reco_score + alpha * score
        kl_div += score * np.log2(score / reco_score)

    return kl_div


def generate_item_candidates(model, user_item, user_id, index2item, item_mapping,
                             filter_already_liked_items=True):
    """
    For a given user, generate the list of items that we can recommend, during this
    step, we will also attach the recommender's score to each item.
    """
    n_items = user_item.shape[1]

    # this is how implicit's matrix factorization generates
    # the scores for each item for a given user, modify this
    # part of the logic if we were to use a completely different
    # algorithm to generate the ranked items
    user_factor = model.user_factors[user_id]
    scores = model.item_factors.dot(user_factor)

    liked = set()
    if filter_already_liked_items:
        liked = set(user_item[user_id].indices)

    item_ids = set(np.arange(n_items))
    item_ids -= liked

    items = []
    for item_id in item_ids:
        if index2item[item_id] in item_mapping.keys():
            item = item_mapping[index2item[item_id]]
            item.score = scores[item_id]
            items.append(item)

    return items



def compute_utility(reco_items, interacted_distr, lmbda=0.5):
    """
    Our objective function for computing the utility score for
    the list of recommended items.

    lmbda : float, 0.0 ~ 1.0, default 0.5
        Lambda term controls the score and calibration tradeoff,
        the higher the lambda the higher the resulting recommendation
        will be calibrated. Lambda is keyword in Python, so it's
        lmbda instead ^^
    """
    reco_distr = compute_genre_distr(reco_items)
    kl_div = compute_kl_divergence(interacted_distr, reco_distr)

    total_score = 0.0
    for item in reco_items:
        total_score += item.score

    # kl divergence is the lower the better, while score is
    # the higher the better so remember to negate it in the calculation
    utility = (1 - lmbda) * total_score - lmbda * kl_div
    return utility


def calib_recommend(items, interacted_distr, topn, lmbda=0.5):
    """
    start with an empty recommendation list,
    loop over the topn cardinality, during each iteration
    update the list with the item that maximizes the utility function.
    """
    calib_reco = []
    best_item = None
    for _ in range(topn):
        max_utility = -np.inf
        for item in items:
            if item in calib_reco:
                continue

            utility = compute_utility(calib_reco + [item], interacted_distr, lmbda)
            if utility > max_utility:
                max_utility = utility
                best_item = item

        calib_reco.append(best_item)

    return calib_reco




def calib_recommend(items, interacted_distr, topn, lmbda=0.5):
    """
    start with an empty recommendation list,
    loop over the topn cardinality, during each iteration
    update the list with the item that maximizes the utility function.
    """
    best_item = None
    calib_reco = []
    for _ in range(topn):
        max_utility = -np.inf
        for item in items:
            if item in calib_reco:
                continue

            utility = compute_utility(calib_reco + [item], interacted_distr, lmbda)
            if utility > max_utility:
                max_utility = utility
                best_item = item

        calib_reco.append(best_item)

    return calib_reco

def distr_comparison_plot(interacted_distr, reco_distr, width=0.3):
    # the value will automatically be converted to a column with the
    # column name of '0'
    interacted = pd.DataFrame.from_dict(interacted_distr, orient='index')
    reco = pd.DataFrame.from_dict(reco_distr, orient='index')
    df = interacted.join(reco, how='outer', lsuffix='_interacted')

    n = df.shape[0]
    index = np.arange(n)
    plt.barh(index, df['0_interacted'], height=width, label='interacted distr')
    plt.barh(index + width, df['0'], height=width, label='reco distr')
    plt.yticks(index, df.index)
    plt.legend(bbox_to_anchor=(1, 0.5))
    plt.title('Genre Distribution between User Historical Interaction v.s. Recommendation')
    plt.ylabel('Genre')
    plt.show()

def show_genre_dist(items_interacted):
    # we can check that the probability does in fact add up to 1
    print(compute_genre_distr(items_interacted))

