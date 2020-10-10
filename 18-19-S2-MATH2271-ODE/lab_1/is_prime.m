function result = is_prime(n)
%IS_PRIME Summary of this function goes here
%   Detailed explanation goes here
result = true;
for i = 2:(n-1)
    if(mod(n,i) == 0)
        result = false;
        break;
    end
end
end

