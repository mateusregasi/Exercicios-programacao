from transformers import AutoTokenizer, AutoModelForCausalLM, TrainingArguments, Trainer
from peft import LoraConfig, get_peft_model
import datasets

model_name = "meta-llama/Meta-Llama-3-8B" 
# data = datasets.load_dataset("json", data_files="meu_dataset.json")

tokenizer = AutoTokenizer.from_pretrained(model_name)
tokenizer.pad_token = tokenizer.eos_token

def tokenize(batch):
    return tokenizer(
        batch["text"],
        padding=True,
        truncation=True,
        max_length=512
    )

data = data.map(tokenize, batched=True)

model = AutoModelForCausalLM.from_pretrained(
    model_name,
    load_in_4bit=True,             # QLoRA
    device_map="auto"
)

lora_cfg = LoraConfig(
    r=16,
    lora_alpha=32,
    lora_dropout=0.05,
    target_modules=["q_proj", "v_proj"]  # módulos clássicos do LLaMA
)

model = get_peft_model(model, lora_cfg)

args = TrainingArguments(
    output_dir="llama3-ft",
    per_device_train_batch_size=1,
    gradient_accumulation_steps=16,
    warmup_steps=50,
    max_steps=500,
    learning_rate=2e-4,
    fp16=True,
    logging_steps=10
)

trainer = Trainer(
    model=model,
    train_dataset=data["train"],
    args=args
)

trainer.train()

model.save_pretrained("llama3-ft-final")