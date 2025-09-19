export OLLAMA_CUDA=1               # liga o backend GPU
export CUDA_VISIBLE_DEVICES=0      # escolhe qual GPU usar
export OLLAMA_NUM_GPU=1            # quantas GPUs o Ollama deve alocar
ollama serve