from classifier import ClassifierModel
from tokenizer import ClassifierTokenizer
from encoder import Encoder

import torch

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
model = ClassifierModel().to(device)
tokenizer = ClassifierTokenizer()
encoder = Encoder(device)

model.load_state_dict(
    torch.load("classifier_model.pt")
)
model.eval()

titulo = "The questions that 800,000 people are waiting for Trump and Jeff Sessions to answer about DACA",
frase = "News\n\nThe Number Of Desperate Immigrants Who Die While Trying To Get Into The US Keeps Rising"

def predict(content, title, return_probs=False, label_map=None):
    tokenized_title = tokenizer.tokenize(title)
    tokenized_content = tokenizer.tokenize(content)

    title_emb = encoder.mean_pooling(
        encoder.encode(tokenized_title),
        tokenized_title["attention_mask"]
    )
    content_emb = encoder.mean_pooling(
        encoder.encode(tokenized_content),
        tokenized_content["attention_mask"]
    )

    title_emb = title_emb.to(device)
    content_emb = content_emb.to(device)

    with torch.no_grad():
        logits = model(title_emb, content_emb)
        probs = torch.softmax(logits, dim=1).cpu().numpy()
        pred_idx = int(probs.argmax(axis=1)[0])

    if return_probs:
        return pred_idx if label_map is None else label_map[pred_idx], probs[0]
    return (pred_idx if label_map is None else label_map[pred_idx])

print(predict(frase, titulo))