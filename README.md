## Onde é usado?
**Gerenciamento de Entidades em Jogos**: Muitos motores de jogos implementam estruturas semelhantes para gerenciar entidades no jogo. Cada entidade pode ter um ID único e precisam ser adicionadas e removidas dinamicamente.

**Sistemas de Física e Simulação**: Em simulações físicas complexas, é comum precisar gerenciar um grande número de objetos que interagem entre si. Uma estrutura de dados eficiente é essencial para lidar com a adição, remoção e consulta desses objetos.
Sistemas de Gerenciamento de Memória.

**Sistemas Embarcados e de Baixo Nível**: Em sistemas com recursos limitados de memória, é crucial ter estruturas de dados que otimizem o uso da memória disponível.

**Gerenciamento de Memória Personalizado**: Em certos sistemas ou ambientes de programação, pode ser necessário implementar estruturas de dados personalizadas para lidar com o gerenciamento de memória de maneira específica.


### Documentação do SparseDenseSet

O SparseDenseSet é uma estrutura de dados que combina características de conjuntos esparsos e densos, proporcionando eficiência de memória e acesso rápido a objetos por meio de IDs únicos. Esta documentação detalha as principais características, métodos e uso recomendado do SparseDenseSet.

#### Estrutura de Dados

O SparseDenseSet é composto por três componentes principais:

1. **mVersion:** Um vetor que armazena a versão de cada objeto. Cada objeto tem uma versão associada que permite a reciclagem eficiente de IDs.
   
2. **mIndexes:** Um vetor de índices que mapeia para os objetos armazenados. Estes índices são referenciados pelos IDs únicos dos objetos.
   
3. **mData:** Um vetor de ponteiros únicos para os objetos. Os objetos em si são armazenados dinamicamente e apontados por estes ponteiros.

#### Métodos Principais

- **`bool contains(uint64_t id) const`**
  - Verifica se um objeto com o ID fornecido está presente no SparseDenseSet.
  - **Parâmetros:**
    - `id`: O ID único do objeto a ser verificado.
  - **Retorno:**
    - `true` se o objeto com o ID fornecido está presente, `false` caso contrário.

- **`uint16_t size() const`**
  - Retorna o número de objetos armazenados no SparseDenseSet.
  - **Retorno:**
    - O número de objetos armazenados como um `uint16_t`.

- **`uint64_t insert(std::unique_ptr<T> data)`**
  - Insere um novo objeto no SparseDenseSet.
  - **Parâmetros:**
    - `data`: Um ponteiro único para o objeto a ser inserido.
  - **Retorno:**
    - O ID único associado ao objeto inserido.
    - Retorna `INVALID_ID` se o limite de 65536 objetos for atingido.

- **`bool remove(uint64_t id)`**
  - Remove o objeto com o ID fornecido do SparseDenseSet.
  - **Parâmetros:**
    - `id`: O ID único do objeto a ser removido.
  - **Retorno:**
    - `true` se o objeto foi removido com sucesso, `false` se o objeto não existia.

- **`T* get(uint64_t id) const`**
  - Recupera o ponteiro para o objeto com o ID fornecido.
  - **Parâmetros:**
    - `id`: O ID único do objeto a ser recuperado.
  - **Retorno:**
    - Um ponteiro para o objeto se encontrado, `nullptr` se o objeto não existir.

#### Limitações

- **Limite de Objetos:** O SparseDenseSet pode conter até 65536 objetos simultaneamente devido ao uso de 16 bits para o índice.
  
- **Reciclagem de IDs:** A reciclagem de IDs é possível graças à divisão de 64 bits em 16 bits para o índice e 48 bits para a versão. Isso permite mais de 281 trilhões de reciclagens antes que IDs comecem a se repetir.

#### Uso Recomendado

O SparseDenseSet é recomendado para cenários em que há uma alta taxa de inserção e remoção de objetos e onde o acesso rápido aos objetos por meio de IDs únicos é crucial. Alguns casos de uso incluem:

- **Motores de Jogos:** Para gerenciar entidades em um jogo com eficiência de memória e acesso rápido.
  
- **Sistemas de Simulação:** Para lidar com uma grande quantidade de entidades ou objetos simulados.
  
- **Aplicações Reativas:** Onde a criação e destruição de objetos é frequente, como em interfaces de usuário dinâmicas.

### Exemplo de Uso

```cpp
SparseDenseSet<Entity> entitySet;

// Inserir uma entidade
std::unique_ptr<Entity> entity1 = std::make_unique<Entity>();
uint64_t id1 = entitySet.insert(std::move(entity1));

// Verificar se a entidade está no SparseDenseSet
if (entitySet.contains(id1)) {
    // Recuperar a entidade
    Entity* retrievedEntity = entitySet.get(id1);
    if (retrievedEntity) {
        // Usar a entidade
    }
}

// Remover a entidade
if (entitySet.remove(id1)) {
    // Entidade removida com sucesso
}
```

Neste exemplo, uma entidade Entity é inserida no SparseDenseSet, verificada, recuperada e removida. Certifique-se de substituir Entity pelo tipo de objeto que deseja armazenar no SparseDenseSet.


