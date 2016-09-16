%Nash Equilibrium: two player, two strategies, non-symmetric game
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Step 1: Initiate two payoff matrices.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
P1=[5 0;
15 10];
P2=[5 15;
0 10];
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Step 2: Create an isolated payoff vector (IPV) for each player and each
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Player 1
C1=P1(:,1);
D1=P1(:,2);
%Player 2
C2=P2(1,:);
D2=P2(2,:);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Step 3: Find the best response functions for each player
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Player 1
[br11 bri11]=max(C1);
[br12 bri12]=max(D1);
%Player 2
[br21 bri21]=max(C2);
[br22 bri22]=max(D2);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Step 4: Find the Nash Equilibrium(s)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if (bri11==bri12) %P1 has a strictly dominant strategy
if (bri21==bri22) %P2 has a strictly dominant strategy
nash=[bri11 bri21];
elseif (bri21~=bri22) %P2 does NOT have a strictly dominant strategy
if (bri11==1)
nash=[bri11 bri21];
elseif (bri11==2)
nash=[bri11 bri22];
end;
end;
elseif (bri11~=bri12) %P1 does NOT have a strictly dominant strategy
if (bri21==bri22) %P2 has a strictly dominant strategy
if (bri21==1)
nash=[bri11 bri21];
elseif (bri21==2)
nash=[bri12 bri21];
end;
elseif (bri21~=bri22) %P2 does NOT have a strictly dominant strategy (no
dominant strategies)
if (bri11==bri21)
if (bri11==1)
nash1=[bri11 bri21];
elseif (bri11==2)
if (bri12==1)
nash1=[bri12 bri21];
elseif (bri12==2)
nash1=[0 0];
end;
end;
elseif (bri11~=bri21)
nash1=[0 0];
end;
if (bri12==bri22)
if (bri12==2)
nash2=[bri12 bri22];
elseif (bri12==1)
if (bri11==2)
nash2=[bri11 bri22];
elseif (bri11==1)
nash2=[0 0];
end;
end;
elseif (bri12~=bri22)
nash2=[0 0];
end;
if (nash1==nash2)
nash=nash1;
elseif (nash1~=nash2)
nash=[nash1;
nash2];
end;
end;
end;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Step 5: Display the Nash Equilibrium output.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%