import torch
from conf import MODEL_NAME

class ClassifierModel(torch.nn.Module):
    def __init__(self, hidden=768):
        super().__init__()
        
        dropout=0.3
        input_dim = hidden * 2
        self.dropout = torch.nn.Dropout(dropout)
        self.classifier = torch.nn.Sequential(
            torch.nn.Linear(input_dim, hidden),
            torch.nn.ReLU(),
            torch.nn.LayerNorm(hidden),
            torch.nn.Dropout(dropout),
            torch.nn.Linear(hidden, hidden // 2),
            torch.nn.ReLU(),
            torch.nn.Dropout(dropout),
            torch.nn.Linear(hidden // 2, 3)
        )

    def forward(self, title_emb, message_emb):
        x = torch.cat([title_emb, message_emb], dim=-1)
        x = self.dropout(x)
        logits = self.classifier(x)
        return logits