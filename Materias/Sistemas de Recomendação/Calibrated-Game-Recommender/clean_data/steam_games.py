import ast
import json
import pandas as pd

filepath = '../data/steam_games.json'
writefilepath = '../data_csv/steam_games.csv'


df = pd.DataFrame(columns = ['name','genres','publisher','developer','price'])

count = 0
with open(filepath,encoding='gb18030',errors='ignore') as f:
# 	single_game = 0
    for line in f:
      l = ast.literal_eval(line)	# Convert single quotes in json to proper double quotes
      #print(l)
      
      if "id" not in l:
        print(l)
        continue
      
      if "title" in l:
        name = l["title"]
      elif "app_name" in l:
        name = l["app_name"]
      else:
        name = 0
        print(l)
      
      if "publisher" in l:
        publisher = l["publisher"]
      else:
        publisher = 0


      if "developer" in l:
        developer = l["developer"]
      else:
        developer = 0
      
      if "genres" in l:
        genres = l["genres"]
      elif "tags" in l:
        genres = l["tags"]
      else:
        genres = 0
        
      if "price" not in l or not isinstance(l["price"], float):
        price = 0
      else:
        price = l["price"]
      
      df.loc[int(l["id"])] = pd.Series({'name': name,'genres': genres,'publisher': developer,'developer': publisher,'price': price,}) 

print("Size = {}\nShape ={}". format(df.size, df.shape)) 
df = df.sort_index()
df.to_csv(writefilepath, encoding='utf_8_sig')