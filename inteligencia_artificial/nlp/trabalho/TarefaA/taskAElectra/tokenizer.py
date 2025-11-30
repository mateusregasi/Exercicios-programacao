class ClassifierTokenizer:

    def __init__(self):
        from transformers import AutoTokenizer
        from conf import MODEL_NAME, MAX_LENGTH_TOKENS
        self.model_name = MODEL_NAME
        self.max_length = MAX_LENGTH_TOKENS
        self.tokenizer = AutoTokenizer.from_pretrained(MODEL_NAME, use_fast=True)

    def tokenize(self, string):
        return self.tokenizer(
            string,
            return_tensors="pt",
            padding="max_length",
            truncation=True,
            max_length=self.max_length,
        )