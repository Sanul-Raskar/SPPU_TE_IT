#!/bin/sh

opt=1
while [ $opt -ne 7 ]
do
  echo
  echo "------------------ "
  echo "Student Database"
  echo
  echo "1.Create the database"
  echo "2.Insert a record"
  echo "3.Search a record"
  echo "4.Modify a record"
  echo "5.Delete a record"
  echo "6.Display"
  echo "7.Exit"
  echo "-------------------"
  read opt

  case $opt in
    1)
      echo
      echo "-------------------"
      echo "| CREATE DATABASE |"
      echo "-------------------"
      echo
      echo "How many records you want to insert?"
      read n
      count=0
      while [ $count -ne $n ]
      do

        echo "Please enter Student Information"
        echo "Enter the roll number"
        read roll
        echo "Enter the Name"
        read name
        echo "Enter branch"
        read branch
        record="$roll $name  $branch"
        `echo $record | cat >> db.txt`
        count=$(($count+1))
      done
      echo "Record inserted successfully!"
      ;;

    2)
      echo
      echo "----------"
      echo "| INSERT |"
      echo "----------"
      echo
      echo "Please enter Student Information"
      echo "Enter the roll number"
      read roll
      echo "Enter the Name"
      read name
      echo "Enter branch"
      read branch
      record="$roll $name  $branch"
      `echo $record | cat >> db.txt`

      ;;
    3)
      echo
      echo "----------"
      echo "| SEARCH |"
      echo "----------"
      echo
      echo "Enter name/roll_no to search"
      read key
      if grep -q $key db.txt; then
        echo "Record found successfully"
        grep -n $key db.txt
      else
        echo "Record not found :("
      fi

      ;;
    4)
      echo
      echo "----------"
      echo "| MODIFY |"
      echo "----------"
      echo
      echo "enter roll no. to be modified"
      read n

      var=`grep -n  ^$n db.txt | cut -c 1`
      var1=` expr $var - 1 `
      head -$var1 db.txt | cat > temp

      echo "Enter new Information"
      echo "Enter the roll number"
      read roll
      echo "Enter the Name"
      read name
      echo "Enter branch"
      read branch
      record="$roll $name  $branch"
      echo $record | cat >> db.txt
      var2=` wc -l < db.txt `
      var3=` expr $var2 - $var `
      tail -$var3 db.txt | cat >> temp
      mv temp db.txt
      ;;

    5)
      echo
      echo "----------"
      echo "| DELETE |"
      echo "----------"
      echo
      echo "Enter Roll number to be deleted"
      read n
      if grep -q $n db.txt; then
        echo "Record deleted successfully"
      else
        echo "Record not found :("
      fi

      grep -v ^$n db.txt | cat > temp
      mv temp db.txt
      ;;

    6)
      echo
      echo "-----------"
      echo "| DISPLAY |"
      echo "-----------"
      echo
      echo "----------------------------"
      echo "Name   Roll No.  Branch "
      cat db.txt
      echo "----------------------------"
      echo
      ;;

    7)
      echo "GoodBye!"
      ;;

    *)
      echo "Please select valid option"
      ;;
  esac

done

# OUTPUT
#
# sanul@sanul-HP-Notebook:~/Desktop$ chmod +x database.sh
# sanul@sanul-HP-Notebook:~/Desktop$ ./database.sh
#
# ------------------
# Student Database
#
# 1.Create the database
# 2.Insert a record
# 3.Search a record
# 4.Modify a record
# 5.Delete a record
# 6.Display
# 7.Exit
# -------------------
# 1
#
# -------------------
# | CREATE DATABASE |
# -------------------
#
# How many records you want to insert?
# 3
# Please enter Student Information
# Enter the roll number
# 1
# Enter the Name
# Sanul
# Enter branch
# IT
# Please enter Student Information
# Enter the roll number
# 2
# Enter the Name
# Manas
# Enter branch
# IT
# Please enter Student Information
# Enter the roll number
# 3
# Enter the Name
# Sachin
# Enter branch
# Comp
# Record inserted successfully!
#
# ------------------
# Student Database
#
# 1.Create the database
# 2.Insert a record
# 3.Search a record
# 4.Modify a record
# 5.Delete a record
# 6.Display
# 7.Exit
# -------------------
# 6
#
# -----------
# | DISPLAY |
# -----------
#
# ----------------------------
# Name   Roll No.  Branch
# 1 Sanul IT
# 2 Manas IT
# 3 Sachin Comp
# ----------------------------
#
#
# ------------------
# Student Database
#
# 1.Create the database
# 2.Insert a record
# 3.Search a record
# 4.Modify a record
# 5.Delete a record
# 6.Display
# 7.Exit
# -------------------
# 3
#
# ----------
# | SEARCH |
# ----------
#
# Enter name/roll_no to search
# 1
# Record found successfully
# 1:1 Sanul IT
#
# ------------------
# Student Database
#
# 1.Create the database
# 2.Insert a record
# 3.Search a record
# 4.Modify a record
# 5.Delete a record
# 6.Display
# 7.Exit
# -------------------
# 3
#
# ----------
# | SEARCH |
# ----------
#
# Enter name/roll_no to search
# Manas
# Record found successfully
# 2:2 Manas IT
#
# ------------------
# Student Database
#
# 1.Create the database
# 2.Insert a record
# 3.Search a record
# 4.Modify a record
# 5.Delete a record
# 6.Display
# 7.Exit
# -------------------
# 4
#
# ----------
# | MODIFY |
# ----------
#
# enter roll no. to be modified
# 3
# Enter new Information
# Enter the roll number
# 5
# Enter the Name
# New
# Enter branch
# Entc
#
# ------------------
# Student Database
#
# 1.Create the database
# 2.Insert a record
# 3.Search a record
# 4.Modify a record
# 5.Delete a record
# 6.Display
# 7.Exit
# -------------------
# 6
#
# -----------
# | DISPLAY |
# -----------
#
# ----------------------------
# Name   Roll No.  Branch
# 1 Sanul IT
# 2 Manas IT
# 5 New Entc
# ----------------------------
#
#
# ------------------
# Student Database
#
# 1.Create the database
# 2.Insert a record
# 3.Search a record
# 4.Modify a record
# 5.Delete a record
# 6.Display
# 7.Exit
# -------------------
# 5
#
# ----------
# | DELETE |
# ----------
#
# Enter Roll number to be deleted
# 5
# Record deleted successfully
#
# ------------------
# Student Database
#
# 1.Create the database
# 2.Insert a record
# 3.Search a record
# 4.Modify a record
# 5.Delete a record
# 6.Display
# 7.Exit
# -------------------
# 6
#
# -----------
# | DISPLAY |
# -----------
#
# ----------------------------
# Name   Roll No.  Branch
# 1 Sanul IT
# 2 Manas IT
# ----------------------------
#
#
# ------------------
# Student Database
#
# 1.Create the database
# 2.Insert a record
# 3.Search a record
# 4.Modify a record
# 5.Delete a record
# 6.Display
# 7.Exit
# -------------------
# 5
#
# ----------
# | DELETE |
# ----------
#
# Enter Roll number to be deleted
# 7
# Record not found :(
#
# ------------------
# Student Database
#
# 1.Create the database
# 2.Insert a record
# 3.Search a record
# 4.Modify a record
# 5.Delete a record
# 6.Display
# 7.Exit
# -------------------
# 6
#
# -----------
# | DISPLAY |
# -----------
#
# ----------------------------
# Name   Roll No.  Branch
# 1 Sanul IT
# 2 Manas IT
# ----------------------------
#
#
# ------------------
# Student Database
#
# 1.Create the database
# 2.Insert a record
# 3.Search a record
# 4.Modify a record
# 5.Delete a record
# 6.Display
# 7.Exit
# -------------------
# 7
# GoodBye!
# sanul@sanul-HP-Notebook:~/Desktop$
#
