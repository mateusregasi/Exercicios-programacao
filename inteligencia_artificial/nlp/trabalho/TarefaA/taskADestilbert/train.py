import torch
from conf import NUM_EPOCHS, BATCH_SIZE, NORMALIZED_TRAIN_FILE, NORMALIZED_DEV_FILE
from dataset import MyDataset
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score
import numpy as np
from classifier import ClassifierModel

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    
training_set = MyDataset(NORMALIZED_TRAIN_FILE, device)
dev_set = MyDataset(NORMALIZED_DEV_FILE, device)

classifier = ClassifierModel().to(device)
criterion = torch.nn.CrossEntropyLoss()
optimizer = torch.optim.AdamW(classifier.parameters(), lr=2e-3, weight_decay=1e-2)
# optimizer = torch.optim.SGD(classifier.parameters(), momentum=0.9)
scheduler = torch.optim.lr_scheduler.CosineAnnealingLR(optimizer, T_max=10)

train_loader = torch.utils.data.DataLoader(
    training_set,
    batch_size=BATCH_SIZE, 
    shuffle=True
)

dev_loader = torch.utils.data.DataLoader(
    dev_set,
    batch_size=BATCH_SIZE,
    shuffle=False
)

all_preds = []
all_labels = []

# Early stopping
patience = 5
best_val_loss = float('inf')
patience_counter = 0

for epoch in range(NUM_EPOCHS):
    classifier.train()
    epoch_loss = 0
    epoch_preds = []
    epoch_labels = []
    
    for title, content, label in train_loader:
        title, content, label = title.to(device), content.to(device), label.to(device)
        optimizer.zero_grad()

        logits = classifier(title, content)
        loss = criterion(logits, label)
        
        loss.backward()
        optimizer.step()
        
        epoch_loss += loss.item()
        
        # Guardar predições para métricas
        preds = torch.argmax(logits, dim=1).cpu().numpy()
        labels_np = label.cpu().numpy()
        epoch_preds.extend(preds)
        epoch_labels.extend(labels_np)
    
    # Calcular métricas do epoch de treino
    accuracy = np.mean(np.array(epoch_preds) == np.array(epoch_labels))
    precision = np.mean([np.mean(np.array(epoch_preds)[np.array(epoch_labels) == i] == i) for i in range(3) if np.sum(np.array(epoch_labels) == i) > 0])
    recall = np.mean([np.mean(np.array(epoch_preds)[np.array(epoch_labels) == i] == i) for i in range(3) if np.sum(np.array(epoch_labels) == i) > 0])
    
    avg_loss = epoch_loss / len(train_loader)
    
    # Validação
    classifier.eval()
    val_loss = 0
    val_preds = []
    val_labels = []
    
    with torch.no_grad():
        for title, content, label in dev_loader:
            title, content, label = title.to(device), content.to(device), label.to(device)
            logits = classifier(title, content)
            loss = criterion(logits, label)
            
            val_loss += loss.item()
            preds = torch.argmax(logits, dim=1).cpu().numpy()
            labels_np = label.cpu().numpy()
            val_preds.extend(preds)
            val_labels.extend(labels_np)
    
    avg_val_loss = val_loss / len(dev_loader)
    val_accuracy = np.mean(np.array(val_preds) == np.array(val_labels))
    
    print(f"epoch {epoch} — train_loss {avg_loss:.4f} — accuracy {accuracy:.4f} — precision {precision:.4f} — recall {recall:.4f} — val_loss {avg_val_loss:.4f} — val_acc {val_accuracy:.4f}")
    
    # Early stopping
    if avg_val_loss < best_val_loss:
        best_val_loss = avg_val_loss
        patience_counter = 0
        torch.save(classifier.state_dict(), "classifier_model.pt")
        print(f"  ✓ Melhor modelo salvo (val_loss: {avg_val_loss:.4f})")
    else:
        patience_counter += 1
        print(f"  → Sem melhora ({patience_counter}/{patience})")
        if patience_counter >= patience:
            print(f"\n⛔ Early stopping acionado após {epoch + 1} epochs!")
            break
    
    scheduler.step()

print("\nModelo final carregado: classifier_model.pt")