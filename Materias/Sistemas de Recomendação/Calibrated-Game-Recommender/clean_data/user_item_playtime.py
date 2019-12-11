max_item_id = 10000  # use as a way to constrict memory errors, increase as needed

import pandas as pd
import ast
import numpy as np
from collections import OrderedDict

filepath = './user_items.json'
writefilepath = '../data_csv/user_items_playtime_' + str(max_item_id) + '.csv'

data = []
game_ids_valid = set()  # We only want to have game ids that appear in any user's game list

num_games_considered = 0  # Just for profiling
num_valid_users = 0  # Also profiling

count = 0
with open(filepath, encoding='gb18030', errors='ignore') as f:
    for line in f:
        l = ast.literal_eval(line)  # Convert single quotes in json to proper double quotes

        # Don't consider a user that doesn't own any games
        if int(l["items_count"]) > 0:
            games = l["items"]
            games_filter = []
            for g in games:
                playtime = g["playtime_forever"]
                if playtime > 0:  # Also don't consider games not played
                    game_id = int(g["item_id"])
                    if game_id <= max_item_id:  # Set limit on games due to space
                        games_filter.append({game_id: playtime})
                        game_ids_valid.add(game_id)
                        num_games_considered += 1

            if len(games_filter) >= 1:
                num_valid_users += 1
                data.append({l["user_id"]: games_filter})

# count = count+1
# print(count)


print(max_item_id)
print(num_games_considered)
print(len(game_ids_valid))
print(num_valid_users)

# Now with format as data (list of nested JSON objects) = 	[	{user_id: [	{item_id: playtime_forever}		]	}	]
# Convert to dataframe where
#		item_id		0		..		max_item_id		
#  user_id 			
#	x1				playtime_forever
#	...
#	xn
#
# 
# Create list of game_id's only based on the valid game ids
game_list = list(game_ids_valid)
game_list = sorted(game_list)
print(*game_list)
games_dict = OrderedDict()

df = pd.DataFrame(columns=list(game_list))
items_list = np.zeros(len(game_list))

for user in data:

    # Clear entries of sorted Dictionary (and creates the first set of key-value pairs)
    for k in game_list:
        games_dict[k] = 0

    key = next(iter(user))  # Note there's only one key. User is {user_id: [...]}
    df.loc[key] = 0
    items = user[key]
    for i in items:
        [(k, v)] = i.items()
        games_dict[k] = v

    # Make the list based on the sorted values in dict
    val = list(games_dict.values())
    for i in range(len(game_list)):
        df.loc[key][game_list[i]] = val[i]

df.to_csv(writefilepath, index=False)
