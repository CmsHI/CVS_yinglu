grep ' 0--5' gsvd >0-5
grep ' 5--10' gsvd >5-10
grep '10--30' gsvd >10-30
grep '30--50' gsvd >30-50
grep '50--70' gsvd >50-70
grep '70--90' gsvd >70-90

./dat.sh 0-5
./dat.sh 5-10
./dat.sh 10-30
./dat.sh 30-50
./dat.sh 50-70
./dat.sh 70-90
