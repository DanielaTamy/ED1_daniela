# 🛒 Simulador de Caixa de Supermercado
Trabalho Prático II — Estrutura de Dados
Implementação de Filas e Prioridade em C

Disciplina: Estrutura de Dados I - Professor Hélcio 

---
## Autores

Daniela Tamy Yuki,
Laura Klemba Cordeiro,
Nathalia Lyra Varela de Albuquerque e
Leonardo de Lima Pereira

---

## 📌 Sobre o Projeto

Este projeto consiste no desenvolvimento de uma aplicação em linguagem C que simula o atendimento em caixas de supermercado utilizando filas comuns e preferenciais.
O sistema foi desenvolvido para aplicação prática dos conceitos de Estrutura de Dados, especificamente filas simples e filas com prioridade, além de registro de estatísticas e simulação de atendimento.

---

## 🧩 Funcionalidades Implementadas
### 1. Cadastro de Cliente
- Nome
- Tipo: comum ou preferencial
- Quantidade de itens

### 2. Inserção nas Filas
- Fila Comum  
- Fila Preferencial  

### 3. Atendimento com Alternância
Regra base: **2 comuns → 1 preferencial**

### 4. Exibição das Filas
Mostra a fila comum e preferencial em tempo real.

### 5. Histórico de Atendimentos
- Tempo estimado  
- Quantidade de itens  

### 6. Estatísticas Finais
- Total de atendimentos por fila  
- Tempo médio  
- Total de itens processados  

## 🗂 Estrutura do Projeto
```
src/
│── main.c
│── clientes.c / clientes.h
│── filas.c / filas.h
│── atendimento.c / atendimento.h
README.md
diario_de_bordo.pdf
```

## ▶️ Como Compilar e Executar
**Compilar:**
```
gcc main.c clientes.c filas.c atendimento.c -o supermercado
```
**Executar:**
```
./supermercado
```

## 🧪 Vídeo de Demonstração
👉 *[Inserir link do YouTube aqui]*

## 👥 Integrantes do Grupo
| Nome | Contribuição |
|------|--------------|
| Nome 1 | Filas |
| Nome 2 | Cadastro |
| Nome 3 | Atendimento |
| Nome 4 | Estatísticas |
| Nome 5 | Integração |

## 📘 Diário de Bordo
See `diario_de_bordo.pdf`.