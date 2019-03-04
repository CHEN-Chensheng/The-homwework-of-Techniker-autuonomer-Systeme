%Path Planning implemented by Q-learning
%% fundamental parameters
episode = 1000;      % times of exploration
alpha = 1;     % learning rate
gamma = 0.8;   % discount factor
state_num = 1120;  % 1120 different states
action_num = 6;  % 6 actions: left up, right up, up£¬down, left down, right down
final_state=930;  % goal state
%Reward Table
R= (-0.01)*ones(1120,6);
R(1093,:)=[-10 -10 -10 -0.01 -10 -0.01]; 
R(1094:1119,:)=ones(26,1)*[-10 -10 -10 -0.01 -0.01 -0.01];
R(1120,:)=[-10 -10 -10 -0.01 -0.01 -10]; 
R(1065,:)=[-10 -10 -10 -0.01 -10 -0.01];
R(1066:1091,:)=ones(26,1)*[-10 -10 -10 -0.01 -0.01 -0.01]; 
R(1092,:)=[-10 -10 -10 -0.01 -0.01 -10];
R(29,:)=[-10 -0.01 -0.01 -10 -10 -10]; 
R(30:55,:)=ones(26,1)*[-0.01 -0.01 -0.01 -10 -10 -10];
R(2:27,:)=ones(26,1)*[-0.01 -0.01 -0.01 -10 -10 -10]; 
R(56,:)=[-0.01 -10 -0.01 -10 -10 -10]; 
R(1,:)=[-10 -0.01 -0.01 -10 -10 -10];
R(28,:)=[-0.01 -10 -0.01 -10 -10 -10];
for i=84:28:1064
 R(i,:)=[-0.01 -10 -0.01 -0.01 -0.01 -10];
end
for i=57:28:1037
 R(i,:)=[-10 -0.01 -0.01 -0.01 -10 -0.01];
end
R(985,6)=1; 
R(986,4)=1;
R(987,5)=1; 
R(873,2)=1; 
R(874,3)=1; 
R(875,1)=1; 
R(1037,:)=[-10 -0.01 -0.01 -10 -10 -10]; 
R(1038,:)=[-0.01 -0.01 -0.01 -10 -10 -10];
R(1039,:)=[-0.01 -0.01 -0.01 -10 -10 -0.01]; 
R(1040,5)=-10;
R(1009:1012,:)=R(1037:1040,:);
R(981:984,:)=R(1037:1040,:);
R(953:956,:)=R(1037:1040,:);
R(925:926,:)=ones(2,1)*[-10 -10 -10 -10 -10 -10];
R(927,:)=[-10 -0.01 -10 -10 -10 -0.01];
R(928,:)=[-10 -0.01 -0.01 -0.01 -10 -0.01];
R(897:898,:)=ones(2,1)*[-10 -10 -10 -0.01 -0.01 -0.01]; 
R(899,:)=[-10 -0.01 -10 -0.01 -0.01 -0.01];
R(900,1)=-10; 
R(869:872,:)=R(897:900,:);
R(841:844,:)=R(897:900,:);
R(813:816,:)=R(897:900,:);
for j=0:28:224
    R(393+j:396+j,:)=R(813+j:816+j,:);
end
Reward_table = R;

%% Update the Q table
% initialize Q(s,a) as zero matrix
Q_table=zeros(state_num,action_num);
for i=1:episode
    %randomly choose a state and let it run 
    %until the car goes to the parking place
    current_state= randperm(state_num,1);
    while current_state~=final_state
        %randomly choose an action from current state
        optional_action=find(Reward_table(current_state,:)>-1);
        if (isempty(optional_action))
            break;
        end
        chosen_action=optional_action(randperm(length(optional_action),1));
        %take action, observe reward and next state
        r=Reward_table(current_state,chosen_action);
        if chosen_action == 1
            next_state = current_state +55;  %  go left-up
        elseif chosen_action == 2
            next_state = current_state +57;  %  go right-up
        elseif chosen_action == 3
            next_state = current_state +56;  %  go up
        elseif chosen_action == 4
            next_state = current_state -56;  %  go down
        elseif chosen_action == 5
            next_state = current_state -57;  %  go left-down
        elseif chosen_action == 6
            next_state = current_state -55; %  go right-down
        end
       
        next_possible_action=find(Reward_table(next_state,:)>-1);
        maxQ=max(Q_table(next_state,next_possible_action));
        % the update formular of q-learning
        Q_table(current_state,chosen_action)=Q_table(current_state,chosen_action)+alpha*(r+gamma*maxQ-Q_table(current_state,chosen_action));
        current_state=next_state;
    end
end

 %% choose the optimal path
currentstate=946;
a=ceil(currentstate/28);
b=currentstate-(a-1)*28;
x=[a];
y=[b];
fprintf('Initialized state %d',currentstate);
fprintf('\n');
while currentstate~=final_state
     %choose action which satisfies Q(s,a)=max{Q(s,a')}
     [maxQtable,index]=max(Q_table(currentstate,:));
     s= find(Q_table(currentstate,:)==max(Q_table(currentstate,:)));
     % if action left-up and left-down have the same Q-value, we first
     % choose left-down.
     if length(s)>1
         index= s(2);
     end
     chosenaction=index;
     if chosenaction == 1
         nextstate = currentstate +55;
     elseif chosenaction == 2
         nextstate = currentstate +57;
     elseif chosenaction == 3
         nextstate = currentstate +56;
     elseif chosenaction == 4
         nextstate = currentstate -56;
     elseif chosenaction == 5
         nextstate = currentstate -57;
     elseif chosenaction == 6
         nextstate = currentstate -55;
     end

     punktx=ceil(nextstate/28);
     punkty=nextstate-(punktx-1)*28;
     x=[x,punktx];
     y=[y,punkty];
     fprintf('the car runs to state %d',nextstate);
     fprintf('\n');
     currentstate=nextstate;
end
%% filter the optimal path 
windowSize =3; 
c = (1/windowSize)*ones(1,windowSize);
d =1;
x1=[a,a,a,a,x];
y2=[b,b,b,b,y];
x2 = filter(c,d,x1);
x2=x2(5:21);
y2=y2(5:21);
figure(2);
plot(y,x);
hold on
plot(y2,x2);
axis([1 28 1 40]);
legend('Input Data','Filtered Data')