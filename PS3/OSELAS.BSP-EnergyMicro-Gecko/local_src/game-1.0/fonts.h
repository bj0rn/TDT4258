char intro[]={
'X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X',
'X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X',
'X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X',
'X', 'X','Y', 'Y','Y', 'Y','X', 'G','G', 'G','G', 'G','G', 'G','X', 'B','X', 'X','X', 'X','X', 'X','X', 'B','X', 'R','R', 'R','R', 'R','R', 'X',
'X', 'X','Y', 'X','X', 'Y','X', 'G','X', 'X','X', 'X','X', 'G','X', 'B','X', 'X','X', 'X','X', 'X','X', 'B','X', 'R','X', 'X','X', 'X','X', 'X',
'X', 'X','Y', 'X','X', 'Y','X', 'G','X', 'X','X', 'X','X', 'G','X', 'B','B', 'X','X', 'X','X', 'X','X', 'B','X', 'R','X', 'X','X', 'X','X', 'X',
'X', 'X','Y', 'X','X', 'Y','X', 'G','X', 'X','X', 'X','X', 'G','X', 'B','X', 'X','X', 'X','X', 'X','X', 'B','X', 'R','X', 'X','X', 'X','X', 'X',
'X', 'X','Y', 'Y','Y', 'Y','X', 'G','X', 'X','X', 'X','X', 'G','X', 'B','X', 'B','X', 'X','X', 'X','X', 'B','X', 'R','X', 'X','X', 'X','X', 'X',
'X', 'X','Y', 'X','X', 'X','X', 'G','X', 'X','X', 'X','X', 'G','X', 'B','X', 'X','X', 'X','X', 'X','X', 'B','X', 'R','X', 'X','X', 'X','X', 'X',
'X', 'X','Y', 'X','X', 'X','X', 'G','X', 'X','X', 'X','X', 'G','X', 'B','X', 'X','B', 'X','X', 'X','X', 'B','X', 'R','X', 'X','X', 'X','X', 'X',
'X', 'X','Y', 'X','X', 'X','X', 'G','X', 'X','X', 'X','X', 'G','X', 'B','X', 'X','X', 'X','X', 'X','X', 'B','X', 'R','X', 'X','X', 'X','X', 'X',
'X', 'X','Y', 'X','X', 'X','X', 'G','X', 'X','X', 'X','X', 'G','X', 'B','X', 'X','X', 'B','X', 'X','X', 'B','X', 'R','X', 'X','X', 'X','X', 'X',
'X', 'X','Y', 'X','X', 'X','X', 'G','X', 'X','X', 'X','X', 'G','X', 'B','X', 'X','X', 'X','X', 'X','X', 'B','X', 'R','X', 'R','R', 'R','R', 'X',
'X', 'X','Y', 'X','X', 'X','X', 'G','X', 'X','X', 'X','X', 'G','X', 'B','X', 'X','X', 'X','B', 'X','X', 'B','X', 'R','X', 'R','X', 'X','R', 'X',
'X', 'X','Y', 'X','X', 'X','X', 'G','X', 'X','X', 'X','X', 'G','X', 'B','X', 'X','X', 'X','X', 'X','X', 'B','X', 'R','X', 'R','X', 'X','R', 'X',
'X', 'X','Y', 'X','X', 'X','X', 'G','X', 'X','X', 'X','X', 'G','X', 'B','X', 'X','X', 'X','X', 'B','X', 'B','X', 'R','X', 'X','X', 'X','R', 'X',
'X', 'X','Y', 'X','X', 'X','X', 'G','X', 'X','X', 'X','X', 'G','X', 'B','X', 'X','X', 'X','X', 'X','X', 'B','X', 'R','X', 'X','X', 'X','R', 'X',
'X', 'X','Y', 'X','X', 'X','X', 'G','X', 'X','X', 'X','X', 'G','X', 'B','X', 'X','X', 'X','X', 'X','X', 'B','X', 'R','X', 'X','X', 'X','R', 'X',
'X', 'X','Y', 'X','X', 'X','X', 'G','X', 'X','X', 'X','X', 'G','X', 'B','X', 'X','X', 'X','X', 'X','X', 'B','X', 'R','X', 'X','X', 'X','R', 'X',
'X', 'X','Y', 'X','X', 'X','X', 'G','X', 'X','X', 'X','X', 'G','X', 'B','X', 'X','X', 'X','X', 'X','B', 'B','X', 'R','X', 'X','X', 'X','R', 'X',
'X', 'X','Y', 'X','X', 'X','X', 'G','G', 'G','G', 'G','G', 'G','X', 'B','X', 'X','X', 'X','X', 'X','X', 'B','X', 'R','R', 'R','R', 'R','R', 'X',
'X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','R', 'X',
'X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X',
'X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X','X', 'X',
};
