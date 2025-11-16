-- https://judge.beecrowd.com/pt/problems/view/2737

(
  select 
    lawyers.name,
    customers_number
  from lawyers
  order by customers_number desc
  limit 1
) union (
  select 
    lawyers.name,
    customers_number
  from lawyers
  order by customers_number asc
  limit 1
) union ( 
  select 
    'Average' as name,
    (sum(customers_number)/count(*)) as customers_number
  from lawyers
);