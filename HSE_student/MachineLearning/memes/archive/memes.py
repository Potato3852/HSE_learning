import pandas as pd

memes_df = pd.read_csv('memes_data.tsv', sep='\t')
templates_df = pd.read_csv('memes_reference_data.tsv', sep = '\t')

memes_df['ImageURL'] = 'https:' + memes_df['ImageURL']
merged_df = pd.merge(memes_df, templates_df, on='MemeLabel', how='left')

print(memes_df['MemeLabel'].value_counts())