import torch

class ClassifierModel(torch.nn.Module):
    def __init__(self, model_name="microsoft/deberta-v3-base", hidden=768):
        super().__init__()
        
        dropout=0.3
        input_dim = hidden * 2
        self.dropout = torch.nn.Dropout(dropout)
        self.classifier = torch.nn.Sequential(
            torch.nn.Linear(input_dim, hidden),
            torch.nn.GELU(),
            torch.nn.LayerNorm(hidden),
            torch.nn.Dropout(dropout),
            torch.nn.Linear(hidden, hidden // 2),
            torch.nn.GELU(),
            torch.nn.Dropout(dropout),
            torch.nn.Linear(hidden // 2, 3)
        )

    def forward(self, title_emb, message_emb):
        x = torch.cat([title_emb, message_emb], dim=-1)
        x = self.dropout(x)
        logits = self.classifier(x)
        return logits