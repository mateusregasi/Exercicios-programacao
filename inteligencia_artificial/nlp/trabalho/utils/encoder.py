import torch

class Encoder:

    def __init__(self, device):
        from transformers import AutoModel
        from .conf import MODEL_NAME

        # Carrega um modelo pré-treinado e associa com o dispositivo de treino
        self.model_encode = AutoModel.from_pretrained(MODEL_NAME)
        self.model_encode.to(device)
        self.device = device

        # Especifica que os parâmetros do modelo não vão ser treinados e seta para inferência
        for param in self.model_encode.parameters():
            param.requires_grad = False
        self.model_encode.eval()

    def encode(self, tokens):
        tokens = {k: v.to(self.model_encode.device) for k, v in tokens.items()}
        return self.model_encode(**tokens).last_hidden_state
    
    def mean_pooling(self, last_hidden_state, attention_mask):
        mask = attention_mask.unsqueeze(-1).expand(last_hidden_state.size()).float().to(self.device)
        summed = (last_hidden_state * mask).sum(1)
        counts = mask.sum(1).clamp(min=1e-9)
        return (summed / counts).squeeze(1)

    def pooling(self, title, content):
        return torch.cat([title, content, title - content, title * content], dim=-1)