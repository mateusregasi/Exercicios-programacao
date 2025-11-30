from transformers import AutoTokenizer, AutoModel
import transformers
print(transformers.__version__)


MODEL_NAME = "microsoft/deberta-v3-base"

tokenizer = AutoTokenizer.from_pretrained(
    MODEL_NAME, 
    use_fast=False
)

model = AutoModel.from_pretrained(MODEL_NAME)