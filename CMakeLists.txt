cmake_minimum_required(VERSION 3.15)
project(WordCardApp)

set(CMAKE_CXX_STANDARD 11)

add_executable(WordCardApp main.cpp WordBook.cpp WordBook.h StudyModule.cpp StudyModule.h Application.cpp Application.h RevisionModule.cpp NoteBook.cpp)