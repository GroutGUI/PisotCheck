%Scott Balchin 14/6/17
%MATLAB
%Function which returns the coefficients of matrix A using the LeVerrier iterative method

function res = Leverrier(A)

C = A;
n = size(A,1);
res = zeros(1,n);

for k = 1:n   
    if k>1 
       C = A*(C + res(n-k+2)*eye(n));
    end
    res(n-k+1) = -trace(C)/k;
end