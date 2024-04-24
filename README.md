### Descrição do Projeto: SparseDenseSet

O SparseDenseSet é uma estrutura de dados projetada para armazenar objetos de forma eficiente, otimizando o uso de memória e permitindo operações de inserção, remoção e recuperação de objetos por meio de IDs únicos. Esta implementação é especialmente adequada quando há um grande número de objetos que são frequentemente adicionados e removidos, mantendo o acesso rápido aos mesmos.

#### Características Principais:

- **Eficiência de Memória:** Utiliza um esquema de armazenamento que é eficiente em termos de memória, permitindo a manipulação de um grande número de objetos sem ocupar espaço desnecessário.

- **IDs Únicos:** Cada objeto é associado a um ID único de 64 bits, dividido em 16 bits para o índice e 48 bits para a versão, permitindo mais de 281 trilhões de reciclagens de IDs antes que eles comecem a se repetir.

- **Inserção e Remoção Rápidas:** Operações de inserção e remoção são otimizadas para serem rápidas e eficientes, mantendo a integridade dos IDs e minimizando realocações de memória.

- **Reciclagem de IDs:** IDs são reciclados quando objetos são removidos, garantindo que o espaço de ID seja reutilizado de forma eficiente e sem desperdício.

#### Métodos Principais:

- **contains(uint64_t id):** Verifica se um objeto com o ID fornecido está presente no SparseDenseSet.

- **insert(std::unique_ptr<T> data):** Insere um novo objeto no SparseDenseSet, retornando um ID único para o objeto inserido.

- **remove(uint64_t id):** Remove o objeto com o ID fornecido do SparseDenseSet, mantendo a estrutura consistente e reciclando o ID para reutilização.

- **get(uint64_t id):** Recupera o ponteiro para o objeto com o ID fornecido, ou retorna `nullptr` se o objeto não estiver presente.

#### Uso Recomendado:
O SparseDenseSet é recomendado para cenários em que há uma grande quantidade de objetos que são frequentemente adicionados e removidos, como em motores de jogos, sistemas de simulação, ou qualquer aplicação que exija gerenciamento eficiente de memória e acesso rápido a objetos por meio de IDs únicos.

Esta implementação é genérica, permitindo que objetos de qualquer tipo sejam armazenados no SparseDenseSet. Ao usar esta estrutura, os desenvolvedores podem alcançar um equilíbrio entre eficiência de memória e desempenho operacional, garantindo uma manipulação eficiente de coleções dinâmicas de objetos.
