drop database if exists sims;
create database if not exists sims default charset utf8mb4 collate utf8mb4_unicode_ci;
grant all on sims.* to 'sims'@'localhost' identified by 'sims_123.';
grant all on sims.* to 'sims'@'%' identified by 'sims_123.';
grant select,insert,update,delete on phpmyadmin.* to 'sims'@'localhost' identified by 'sims_123.';