import time
from scipy.sparse import csr_matrix
from implicit.bpr import BayesianPersonalizedRanking
from implicit.evaluation import train_test_split, precision_at_k
from ItemClass import *
from calibrated_recommender import *

# Folder containing CSVs
DATA_FILEPATH = 'data_csv'

# Recommender Settings
train_interactions = 70 #how many train interactions
train_percent = 0.8 #percent data set to train

# Calibrated recommender
topn = 10
user_id = 46546
lmbda = 0.5

# Define columns to import
item_col = "item_id"
title_col = "name"
genre_col = "genres"

# Read Game info dataframe
df_games = read_steam_games(DATA_FILEPATH)
df_games['item_id'] = df_games.index

# Create Item Mapping
item_mapping = create_item_mapping(df_games, item_col, title_col, genre_col)

# Read matrix item/playtime
df_matrix = read_user_item_playtime(DATA_FILEPATH)

# Create index for items
index2item = pd.Series(list(df_matrix.columns.values), dtype="category").cat.categories

# Create normalized hours matrix
df_scaled_matrix = normalize_hours_matrix(df_matrix)

# compress matrix
csr_df_matrix = csr_matrix(df_scaled_matrix)
np.random.seed()

# Train
user_item_train, user_item_test = train_test_split(csr_df_matrix, train_percentage=train_percent)
bpr = BayesianPersonalizedRanking(iterations=train_interactions)
bpr.fit(user_item_train.T.tocsr())

print(user_item_train[user_id])
interacted_ids = user_item_train[user_id].nonzero()[1]
index2item = index2item.astype('int32')

interacted_items = [item_mapping[index2item[index]] for index in interacted_ids if
                    index2item[index] in item_mapping.keys()]

# it returns the recommended index and their corresponding score
reco = bpr.recommend(user_id, user_item_train, N=topn)
print(reco)

# map the index to Item
reco_items = [item_mapping[index2item[index]] for index, _ in reco if index2item[index] in item_mapping.keys()]
print(reco_items)


# we can check that the probability does in fact add up to 1
interacted_distr = compute_genre_distr(interacted_items)
reco_distr = compute_genre_distr(reco_items[:topn])



# ================================ Testing and showing Graphics ========================
# change default style figure and font size
plt.rcParams['figure.figsize'] = 10, 8
plt.rcParams['font.size'] = 12

distr_comparison_plot(interacted_distr, reco_distr)
compute_kl_divergence(interacted_distr, reco_distr)

items = generate_item_candidates(bpr, user_item_train, user_id, index2item, item_mapping)
print('number of item candidates:', len(items))

calib_reco_items = calib_recommend(items, interacted_distr, topn, lmbda=0.99)
print(items)

print(calib_reco_items)
calib_reco_items = calib_reco_items[:topn]

print(len(calib_reco_items))
calib_reco_distr = compute_genre_distr(calib_reco_items[:topn])
print(calib_reco_distr)
calib_reco_kl_div = compute_kl_divergence(interacted_distr, calib_reco_distr)
reco_kl_div = compute_kl_divergence(interacted_distr, reco_distr)
print('\noriginal reco kl-divergence score:', reco_kl_div)
print('calibrated reco kl-divergence score:', calib_reco_kl_div)

print(calib_reco_distr)
distr_comparison_plot(interacted_distr, calib_reco_distr)


reco_precision = precision(user_item_test, user_id, reco_items, index2item)
calib_reco_precision = precision(user_item_test, user_id, calib_reco_items, index2item)
print('original reco precision score:', reco_precision)
print('calibrated reco precision score:', calib_reco_precision)

print(items)
calib_reco_items = calib_recommend(items, interacted_distr, topn, lmbda=0.5)

calib_reco_distr = compute_genre_distr(calib_reco_items)
calib_reco_kl_div = compute_kl_divergence(interacted_distr, calib_reco_distr)
calib_reco_precision = precision(user_item_test, user_id, calib_reco_items, index2item)
print('calibrated reco kl-divergence score:', calib_reco_kl_div)
print('calibrated reco precision score:', calib_reco_precision)

calib_reco_distr = compute_genre_distr(calib_reco_items)
distr_comparison_plot(interacted_distr, calib_reco_distr)


reco = bpr.recommend(user_id, user_item_train, N=topn)
reco_items = [item_mapping[index2item[index]] for index, _ in reco if index2item[index] in item_mapping.keys()]
print(reco_items)

interacted_ids = user_item_train[user_id].nonzero()[1]
interacted_items = [item_mapping[index2item[index]] for index in interacted_ids if
                    index2item[index] in item_mapping.keys()]

interacted_distr = compute_genre_distr(interacted_items)
print(interacted_distr)

items = generate_item_candidates(bpr, user_item_train, user_id, index2item, item_mapping)
print(len(items))
calib_reco_items = calib_recommend(items, interacted_distr, topn, lmbda)
print(calib_reco_items)
calib_reco_distr = compute_genre_distr(calib_reco_items)

calib_reco_kl_div = compute_kl_divergence(interacted_distr, calib_reco_distr)
calib_reco_precision = precision(user_item_test, user_id, calib_reco_items, index2item)
print('calibrated reco kl-divergence score:', calib_reco_kl_div)
print('calibrated reco precision score:', calib_reco_precision)
distr_comparison_plot(interacted_distr, calib_reco_distr)

reco_kl_div = compute_kl_divergence(interacted_distr, reco_distr)
reco_precision = precision(user_item_test, user_id, reco_items, index2item)
print('original reco kl-divergence score:', reco_kl_div)
print('original reco precision score:', reco_precision)
distr_comparison_plot(interacted_distr, reco_distr)