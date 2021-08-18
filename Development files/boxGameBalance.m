clear all
close all
clc

%Box colors:    G = green
%               B = blue
%               P = purple
%               O = orange

%Chances for Orange, Purple, Blue, and Green chests in that order
boxChance = [2; 10 ; 25; 50];

%Box id
G = 4;
B = 3;
P = 2;
O = 1;

%Box payout
payout = [10; 4; 1; 0];


%Green payout to balance game odds.
payout(G) = (100 - payout(O)*boxChance(O) - payout(P)*boxChance(P) - payout(B)*boxChance(B))/boxChance(G)

%check if G payout is correct
ABCD = payout(O)*boxChance(O) + payout(P)*boxChance(P) + payout(B)*boxChance(B) + payout(G)*boxChance(G)







