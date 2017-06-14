%Scott Balchin 14/6/17
%MATLAB
%Code that generates irreducible Pisot matrices

%Defining the size of the matrix
size = 8;


while true
	%Generate a size x size binary matrix
	N = randi([0 1], size);

	%Check to see if the matrix is irreducible Pisot, if it is, we print it
	if IrrPisot(N)
   	output = '{';
     
	   for i = 1:size
    	   output = [output '{'];
       for j = 1:size
           output = [output num2str(N(i,j)) ','];
       end
       output = output(1:end-1);
       output = [output '},'];
   end
   
   output = output(1:end-1);
   output = [output '}'];
   
    disp(output)
	end
end


