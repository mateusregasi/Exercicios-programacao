from datasets import load_dataset
from sklearn.model_selection import train_test_split
import pandas as pd

# Carregar os dados
df = pd.read_csv('data.csv', delimiter=';')
print(df.columns)
train_texts, test_texts, train_labels, test_labels = train_test_split(
    df['text'], df['label'], test_size=0.2, random_state=42
)

# Criar datasets
from datasets import Dataset
train_dataset = Dataset.from_dict({'text': train_texts, 'label': train_labels})
test_dataset = Dataset.from_dict({'text': test_texts, 'label': test_labels})

from transformers import AutoTokenizer

tokenizer = AutoTokenizer.from_pretrained('facebook/bart-base')

def tokenize_function(example):
    return tokenizer(example['text'], padding='max_length', truncation=True)

tokenized_train = train_dataset.map(tokenize_function, batched=True)
tokenized_test = test_dataset.map(tokenize_function, batched=True)

from transformers import AutoModelForSequenceClassification

model = AutoModelForSequenceClassification.from_pretrained(
    'facebook/bart-base',
    num_labels=len(set(train_labels))
)

from transformers import Trainer, TrainingArguments

training_args = TrainingArguments(
    output_dir='./results',
    evaluation_strategy='epoch',
    learning_rate=2e-5,
    per_device_train_batch_size=16,
    per_device_eval_batch_size=16,
    num_train_epochs=3,
    weight_decay=0.01,
)

trainer = Trainer(
    model=model,
    args=training_args,
    train_dataset=tokenized_train,
    eval_dataset=tokenized_test,
)

trainer.train()
trainer.evaluate()

def classificar_material(texto):
    inputs = tokenizer(texto, return_tensors="pt", padding=True, truncation=True)
    outputs = model(**inputs)
    predicted_class = outputs.logits.argmax().item()
    return predicted_class