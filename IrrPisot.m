%Scott Balchin 14/6/17
%MATLAB
%Function which checks to see if a matrix A is irreducible Pisot using the Perron condition.

function x = IrrPisot(A)

%We first check for primitivity
if ~Primitive(A)
    x = false;
    return
end

%We then find the coefficients of the characteristic polynomial
res = Leverrier(A);
n = size(res,2);

%Checking if the constant term is non-zero
if res(1) == 0;
    x = false;
    return
end

%Checking if the trace is larger than all all other coefficients as required
if abs(res(n)) > sum(abs(res(1:n-1))) + 1
   x = true;
   return
end

x = false;
