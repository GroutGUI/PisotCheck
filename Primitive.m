%Scott Balchin 14/6/17
%MATLAB
%Function checks primitivity of matrix A

function x  = Primitive(A)

s = size(A,1);

C = A;
difference = 1;
zCount1 = 0;
while difference ~= 0
    C = C*A;
    zCount = numel(C)-nnz(C);
    difference = abs(zCount1 - zCount);
    zCount1 = zCount;
end

if zCount1 == 0
   x = true;
   return
end

x = false;
