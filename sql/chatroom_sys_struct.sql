-- ----------------------------
--  Create database and change database
-- ----------------------------
DROP DATABASE IF EXISTS `chatroom_sys`;
CREATE DATABASE `chatroom_sys` CHARACTER SET 'utf8mb4' COLLATE 'utf8mb4_0900_ai_ci';
USE `chatroom_sys`;


CREATE TABLE User (
    ID INT AUTO_INCREMENT PRIMARY KEY,
    Username VARCHAR(255) NOT NULL,
    PasswordHash VARCHAR(255) NOT NULL,
    Birthday DATE,
    Constellation VARCHAR(20),
    Gender VARCHAR(10),
    Introduction TEXT
)AUTO_INCREMENT = 10000;

CREATE TABLE Friend (
    UserID INT,
    FriendID INT,
    PRIMARY KEY (UserID, FriendID),
    FOREIGN KEY (UserID) REFERENCES User(ID),
    FOREIGN KEY (FriendID) REFERENCES User(ID)
);
