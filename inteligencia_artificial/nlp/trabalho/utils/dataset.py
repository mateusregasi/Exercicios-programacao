import os
import torch
from torch.utils.data import Dataset, DataLoader
from json import loads

class MyDataset(Dataset):

    def __init__(self, path):
        self.path = path
        self.files = list(
            filter(
                lambda x: True if not x.startswith(".") else False, 
                os.listdir(path)
            )
        )

    def __len__(self):
        return len(self.files)

    def __getitem__(self, idx):
        file_name = f"{self.path}/{self.files[idx]}"
        text = "".join(open(file_name).readlines())
        json = loads(text)
        
        return json["title"], json["content"], json["label"]