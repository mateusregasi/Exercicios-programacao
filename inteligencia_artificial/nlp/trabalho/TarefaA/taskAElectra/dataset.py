import os
import torch
from torch.utils.data import Dataset, DataLoader
from random import shuffle

class MyDataset(Dataset):
    def __init__(self, path, device):
        self.path = path
        self.files = [os.path.join(path, f) for f in os.listdir(path)]
        self.device = device

    def __len__(self):
        return len(self.files)

    def __getitem__(self, idx):
        path = self.files[idx]
        example = torch.load(
            f"{self.path}obj_{idx}", 
            map_location=self.device
        )
        return example["title"], example["content"], example["label"]