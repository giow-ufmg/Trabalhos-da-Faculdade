import ast
import json
import pandas as pd

max_game_id = 100

filepath = '../data/australian_users_items.json'
writefilepath = '../data_csv/user_game_names_' + str(max_game_id) + '.csv'

# max_game_id = 99920 for 100k cap
# 				= 19990 for 20k cap
# total cap is 530720

df = pd.DataFrame(columns = ['userid', 'game_names'])

with open(filepath) as f:
	single_game = 0
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
				df.loc[l["user_id"]] = pd.Series({'userid': l["user_id"], 'game_names': games_filter})

print("Size = {}\nShape ={}". 
format(df.size, df.shape)) 

df.to_csv(writefilepath, header=False, index=False)