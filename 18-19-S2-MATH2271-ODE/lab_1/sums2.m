function [S, n, nums] = sums2(x)
S = 0;
n = 0;
nums = [];
while S < x
    r = rand(1);
    nums = [nums, r];
    S = S+r;
    n = n+1;
end
nums
end

