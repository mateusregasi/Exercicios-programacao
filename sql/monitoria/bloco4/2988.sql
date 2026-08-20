-- https://judge.beecrowd.com/pt/problems/view/2988

CREATE TABLE teams (
    id integer PRIMARY KEY,
    name varchar(50)
);

CREATE TABLE matches  (
    id integer PRIMARY KEY,
    team_1 integer,
    team_2 integer,
    team_1_goals integer,
    team_2_goals integer,
    FOREIGN KEY (team_1) REFERENCES teams(id),
    FOREIGN KEY (team_2) REFERENCES teams(id)
);

insert into teams
    (id, name)
values
    (1,'CEARA'),
    (2,'FORTALEZA'),
    (3,'GUARANY DE SOBRAL'),
    (4,'FLORESTA');

insert into  matches
    (id, team_1, team_2, team_1_goals, team_2_goals)
values
    (1,4,1,0,4),
    (2,3,2,0,1),
    (3,1,3,3,0),
    (4,3,4,0,1),
    (5,1,2,0,0),
    (6,2,4,2,1);


select 
    name,
    sum(victories) as victories,
    sum(defeats) as defeats,
    sum(draws) as draws,
    sum(score) as score
from 
    ((select 
        team,
        sum(victories) as victories,
        sum(defeats) as defeats,
        sum(draws) as draws,
        sum(score) as score
    from 
        (
            (
                select 
                    team_1 as team,
                    count(team_1) as victories,
                    0 as defeats,
                    0 as draws,
                    count(team_1) * 3 as score
                from matches where team_1_goals > team_2_goals group by team_1
            ) union (
                select 
                    team_1 as team,
                    0 as victories,
                    count(team_1) as defeats,
                    0 as draws,
                    0 as score
                from matches where team_1_goals < team_2_goals group by team_1
            ) union (
                select 
                    team_1 as team,
                    0 as victories,
                    0 as defeats,
                    count(team_1) as draws,
                    count(team_1) as score
                from matches where team_1_goals = team_2_goals group by team_1
            )
        ) as t
        group by team
    ) union (
        select 
            team,
            sum(victories) as victories,
            sum(defeats) as defeats,
            sum(draws) as draws,
            sum(score) as score
        from 
            (
                (
                    select 
                        team_2 as team,
                        0 as victories,
                        count(team_2) as defeats,
                        0 as draws,
                        0 as score
                    from matches where team_1_goals > team_2_goals group by team_2
                ) union (
                    select 
                        team_2 as team,
                        count(team_2) as victories,
                        0 as defeats,
                        0 as draws,
                        count(team_2) * 3 as score
                    from matches where team_1_goals < team_2_goals group by team_2
                ) union (
                    select 
                        team_2 as team,
                        0 as victories,
                        0 as defeats,
                        count(team_2) as draws,
                        count(team_2) as score
                    from matches where team_1_goals = team_2_goals group by team_2
                )
            ) as t
            group by team
    )) as t join teams as tt
        on (tt.id = team)
group by team
order by score desc;

DROP TABLE matches;
DROP TABLE teams;