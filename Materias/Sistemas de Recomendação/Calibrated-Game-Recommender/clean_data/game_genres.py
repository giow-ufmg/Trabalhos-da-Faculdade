import json
import pandas as pd
import ast
import numpy as np

filepath = '../data/steam_games.json'
writefilepath = '../data_csv/game_genres.csv'

df = pd.DataFrame(columns=["game_name", "genres"])
i = 0

with open(filepath) as f:
    for line in f:
        l = ast.literal_eval(line)  # Convert single quotes in json to proper double quotes

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
            df.loc[i] = pd.Series({'game_name': game, 'genres': genres})
            i += 1

df.to_csv(writefilepath, encoding='utf_8_sig', header=False, index=False)
