# 🏥 Sistema de Agendamento de Consultas em Clínica Universitária

Trabalho Prático I – Estrutura de Dados Lineares com Interface de Aplicação  

Disciplina: Estrutura de Dados I - Professor Hélcio 

---
## Autores

Daniela Tamy Yuki,
Laura Klemba Cordeiro,
Nathalia Lyra Varela de Albuquerque e
Leonardo de Lima Pereira

---
## 🎯 Objetivo Geral

O objetivo deste projeto é desenvolver uma aplicação em linguagem **C** que utilize **estruturas de dados lineares** (listas estáticas, dinâmicas, encadeadas, circulares, duplas ou com cabeçalho) para organizar e gerenciar **agendamentos de consultas** de uma clínica universitária.

O sistema permite o **cadastro e gerenciamento de pacientes e consultas**, integrando conceitos teóricos de estruturas de dados com uma aplicação prática e funcional.

---

## 🧩 Funcionalidades Implementadas

### 👤 Módulo de Pacientes (`paciente.c` / `paciente.h`)
- Cadastrar paciente (nome, CPF, matrícula, curso)  
- Armazenar pacientes em uma lista 

### 📅 Módulo de Agendamentos (`agendamento.c` / `agendamento.h`)
- Cadastrar agendamento (CPF, sala, data e hora)  
- Listar agendamentos por **CPF**  
- Listar agendamentos por **sala**  
- Remover agendamento (por CPF + data)  
- Exibir **histórico completo de agendamentos** (utilizando lista com cabeçalho)

### 🧱 Módulo de Listas (`lista.c` / `lista.h`)
- Implementação da estrutura de lista 
- Funções genéricas para inserção, remoção, busca e exibição de elementos  

### 🖥️ Menu Principal (`main.c`)
Interface interativa no terminal que permite ao usuário:
1. Cadastrar paciente  
2. Cadastrar agendamento  
3. Consultar agendamentos por CPF  
4. Consultar agendamentos por sala  
5. Remover agendamento  
6. Visualizar histórico completo  
7. Sair  

---

## 🧩 Arquivos

📁 sistema_agendamento/   
│              
├── main.c # Menu principal e fluxo do programa  
├── paciente.c # Funções de cadastro e exibição de pacientes   
├── paciente.h  
├── agendamento.c # Funções de controle de agendamentos   
├── agendamento.h  
├── lista.c # Implementação das listas lineares   
├── lista.h   
├── README.md # Documentação do projeto  
└── diario_de_bordo.pdf # Relato do desenvolvimento


---

## 🧠 Estrutura de Dados Utilizada

### Lista encadeada simples
- utilizada no módulo de Pacientes para armazenar dinamicamente os cadastros de forma simples e eficiente.
- **Inserções dinâmicas:** Não há limite fixo de elementos.  
- **Operações básicas suficientes:** O módulo de pacientes realiza principalmente cadastro e consultas, sem necessidade de manipulações complexas.  
- **Leve e eficiente:** Menor sobrecarga estrutural, ideal para dados que só precisam crescer linearmente.


### Lista encadeada com Cabeçalho
- Armazenar e gerenciar agendamentos de consultas (CPF, sala, data e hora).
- **Facilidade de manipulação:** A presença de um nó de cabeçalho simplifica inserções e remoções, evitando casos especiais para o início e fim da lista.  
- **Flexibilidade:** Agendamentos são dados mais dinâmicos — com frequência de cadastro, cancelamento e listagem — exigindo uma estrutura mais robusta.  
- **Organização:** O nó sentinela centraliza informações e facilita o gerenciamento do histórico completo de consultas.  


---