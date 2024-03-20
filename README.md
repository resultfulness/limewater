the plan is as follows

store each cell as an 8 bit value:

   P   K   p   q   n   e   w   s

where:
* P is whether the cell is the start cell
* K is whether the cell is the end cell
* p and q store parent info - parent is at:
  - 00 S
  - 01 E
  - 10 W
  - 11 N
* n, e, w and s store connection info

