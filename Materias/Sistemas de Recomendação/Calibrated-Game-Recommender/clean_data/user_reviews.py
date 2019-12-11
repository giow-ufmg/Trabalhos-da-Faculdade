import json
import pandas as pd
import ast
import numpy as np

filepath = '../data/steam_reviews.json'
writefilepath = '../data_csv/user_reviews.csv'

df = pd.DataFrame(columns = ["userid","reviews"])
i = 0

with open(filepath) as f:
	for line in f:
		l = ast.literal_eval(line)	# Convert single quotes in json to proper double quotes

		reviews = l["reviews"]
		review_list = []

		for r in reviews:
			review_list.append(r["review"])

		if len(review_list) == 0:
			df.loc[i] = pd.Series({"userid": l["user_id"], "reviews": 0})
		else:
			df.loc[i] = pd.Series({"userid": l["user_id"], "reviews": review_list})
		i += 1

df.to_csv(writefilepath)