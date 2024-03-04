IFNDEF:
  Ifndef é usado para que algo não seja redefinido, pois ifndef significa "se não definido", isso fará com que se algo não estiver definido, ele o definirá. Se estiver definido, ele será ignorado para que o programa não cometa erros.

Big O notation:

  Questao: What is the big O notation for the CRUD operations in normal, sorted, and heap files

  Resposta ChatGPT:
    Normal Files:

    Create (Insert): O(1) - Assuming you have direct access to the location where you want to insert the new record.
    Read (Search): O(n) - In the worst case, you may need to scan through all records to find the one you're looking for.
    Update: O(n) - Similar to the Read operation, you may need to locate the record first.
    Delete: O(n) - Similar to Read and Update, you may need to locate the record before deletion.
    
    Sorted Files:
    
    Create (Insert): O(n) - In the worst case, you may need to shift existing records to maintain the sorted order.
    Read (Search): O(log n) - Binary search can be used to locate records in a sorted file.
    Update: O(n) - Similar to Create, you may need to shift records to maintain the sorted order.
    Delete: O(n) - Similar to Create and Update, you may need to shift records after deletion.
    
    Heap Files:
    
    Create (Insert): O(1) - Inserting a new record at the end of the file.
    Read (Search): O(1) - In the worst case, you may need to scan through all records to find the one you're looking for.
    Update: O(1) - Similar to Read operation, you may need to locate the record first.
    Delete: O(n) - Similar to Read and Update, you may need to locate the record before deletion.


Comparacao:
  Como esperado o Create do Sort esta que demora mais para criar porque ele tem que se reorganizar.

  Como esperado o Heap Read Binary esta dando o menor quantidade de tempo porque ele ja esta recebendo o posicao ele tem que ir.

  Como esperado o Heap Update Binary esta dando o menor quantidade de tempo porque ele ja esta recebendo o posicao ele tem que ir.

  Como esperado o Heap Delete Binary esta dando o menor quantidade de tempo porque ele ja esta recebendo o posicao ele tem que ir.