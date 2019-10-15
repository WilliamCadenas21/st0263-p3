# PCAM

The meaning of the PCAM is Partition, Communication, Agglomerate and Map. So we wil try to explain all stepts that dirve us to the final solution implemented with OpenMP and MPI.

## Partitioning

First thing first, we explain the serial implementation and then we will move forward to the OpenMP:

### Serial Solution

For practiciti we will use a board 4x4 to explain this part.

#### Grapical representation

| |1|2|3|4| 
|-|-|-|-|-|
|1|.|.|Q|.|
|2|Q|.|.|.|
|3|.|.|.|Q|
|4|.|Q|.|.| 

#### Algorithm representation

| |1|2|3|4| 
|-|-|-|-|-|
|1|0|0|1|0|
|2|1|0|0|0|
|3|0|0|0|1|
|4|0|1|0|0| 

Then as we can see each queen is placed in a expecific positon on the board represented by a matrix but in our implementation we transform this matrix in a vector, so in this way we don't use a Matrix and insted of that we only put in each place of a vector the number of the row that the queen is placed and the index represent the number of the column.

#### Vector notation 
|index|1|2|3|4| 
|-|-|-|-|-|
||2|4|1|3|

1. The algorithm start form the upper left coner placing a queen on a row of a column verifiying if the position is save and then move to the next column.
2. If the position is not safe the algorithm try to place in the next row until there are no more rows. if this happend it return to the back column and prove with the next row on the last position that it placed this queen.
3. it could be two things: if the movement overpass the number of column, it found a safe board and it sums this combination to the valid combinations. After that it also return one column and prove with the next row in this column like step 2.
4. finaly in certain moment the algorithm return to first column and prove in each row and then it can move down because the rows will be over. in that moment the algorithm stops.

### OpenMP Solution

Ok, knowing that the concet of the partition is simple, we give to each procesor(with OpenMP) a row in the first column to search all the posibles combination on the board but with the condition that this process always be have the first queen in the row that we indicated it. 

Supose that we have four procesor, then each procesor tries to find all posibilitys but the first column always have the queen in the same rows. So they try to iterate and combine from second column onwards.

So we will explain with a grapich:

### Process 1
| |1|2|3|4| 
|-|-|-|-|-|
|1|Q|.|.|.|
|2| |.|.|.|
|3| |.|.|.|
|4| |.|.|.|

### Process 2
| |1|2|3|4| 
|-|-|-|-|-|
|1| |.|.|.|
|2|Q|.|.|.|
|3| |.|.|.|
|4| |.|.|.| 

### Process 3
| |1|2|3|4| 
|-|-|-|-|-|
|1| |.|.|.|
|2| |.|.|.|
|3|Q|.|.|.|
|4| |.|.|.| 

### Process 4
| |1|2|3|4| 
|-|-|-|-|-|
|1| |.|.|.|
|2| |.|.|.|
|3| |.|.|.|
|4|Q|.|.|.| 

Notice that each process has a definited prosition for the first column and then all the dots in the others cells are part of the prove that the algorithm will try realize. 

## Communication

### MPI Solution

The final step is try to find a way to divide this set of posibilites and send to a each node that have procesors that will make the diviton that we explained in the last point. So the solution that we thoght was really simple, we take the rows and dive with the number of nodes. Eg: if we have a board 4x4 and we have 2 nodes for the execution, then 4 rows / 2 nodes = 2 rows, so 2 differents rows are asignated to be resolve by each node.

### Process 3
| |1|2|3|4| 
|-|-|-|-|-|
|1|Node1|.|.|.|
|2|Node1|.|.|.|
|3| |.|.|.|
|4| |.|.|.| 

### Process 4
| |1|2|3|4| 
|-|-|-|-|-|
|1| |.|.|.|
|2| |.|.|.|
|3|Node2|.|.|.|
|4|Node2|.|.|.| 

And then each node has internally a determinated number of processor enable to reach the divition showed in the OpenMp solution. More generally N numbers of rows are dive by P nodes, and this is the set of rows that the master send to each node.

![MPI with OpenMp.1](MPI_OpenMP.png)

## Agglomeration

The comunication is escential because we presume that is better to has a number of N higher than P (N >> P). We want that every node have at least more than one row. In this case this node has the posibility to implement OpenMP whit its threats. So the send of information is simple, there is a root node that send all the set of rows and then wait for all the data coming form each node and reduce to show the answer.

## Mapping

The final step is put together all the code and implement the send of the sets and then inside all node apply OpenMP to resolve the number of rows that we asigned to it.

it is simple and smart and all it was made it by us. ;)
