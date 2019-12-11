import ast
import json
import pandas as pd

max_game_id = 1000

filepath = '../data/australian_users_items.json'
write_filepath = '../data_csv/user_game_info.csv'
df1 = pd.DataFrame(columns = ['userid', 'game_names'])

with open(filepath) as f:
	game_id_list = []
	for line in f:
		l = ast.literal_eval(line)	# Convert single quotes in json to proper double quotes
	
		# Don't consider a user that doesn't own any games
		if int(l["items_count"]) > 0:
			games = l["items"]
			games_filter = []
			for g in games:
				playtime = g["playtime_forever"]
				if playtime > 0:	# Also don't consider games not played
					game_id = int(g["item_id"])
					if game_id <= max_game_id: 		# Set limit on games due to space
						games_filter.append(g["item_name"])
			
			if len(games_filter) >= 1:
				df1.loc[l["user_id"]] = pd.Series({'userid': l["user_id"], 'game_names': games_filter})

filepath = './steam_games.json'

#### NEED TO GET USER_ID WITH GAME_GENRE ###################
df2 = pd.DataFrame(columns = ['userid', 'game_genres'])
df21 = pd.DataFrame(columns = ['game_name', 'genres'])
i = 0

with open(filepath) as f:
	for line in f:
		l = ast.literal_eval(line)	# Convert single quotes in json to proper double quotes

		if "title" in l:
			game = l["title"]
		elif "app_name" in l:
			game = l["app_name"]
		else:
			game = 0

		if "genres" in l:
			genres = l["genres"]
		elif "tags" in l:
			genres = l["tags"]
		else:
			genres = 0

		if game != 0:
			df21.loc[i] = pd.Series({'game_name': game, 'genres': genres})
			i += 1

# Match game_names from df1 with game_name from df21, create set of genres from it (then convert to list) for df2
for row in df1.itertuples():
    genre_list = set()
    for name in row.game_names:
        g = df21[df21.game_name == name]
        for k in g.genres:
            # Should only have one value for k (the list itself)
            # Iterate through the list for its values now
            for l in k:
                genre_list.add(l)
    df2.loc[row.Index] = pd.Series({'userid': row.userid, 'game_genres': list(genre_list)})

filepath = './user_reviews.json'

df3 = pd.DataFrame(columns = ["userid","reviews"])
i = 0

with open(filepath) as f:
	for line in f:
		l = ast.literal_eval(line)	# Convert single quotes in json to proper double quotes

		reviews = l["reviews"]
		review_list = []

		for r in reviews:
			review_list.append(r["review"])

		if len(review_list) == 0:
			df3.loc[i] = pd.Series({"userid": l["user_id"], "reviews": 0})
		else:
			df3.loc[i] = pd.Series({"userid": l["user_id"], "reviews": review_list})
		i += 1

df = df1.merge(df2, how='left', on='userid').merge(df3.drop_duplicates(subset=['userid']), how='left', on='userid')
df = df.fillna(0)


df.to_csv(write_filepath, header=False, index=False)

