# https://github.com/cdrx/docker-pyinstaller

sudo docker run --rm -v "$(pwd):/src/" cdrx/pyinstaller-linux -c \
"pyinstaller genHTMLtext.py --onedir --onefile --clean && \
mv dist/genHTMLtext genHTMLtext && \
rm -rf __pycache__/ build/ dist/ genHTMLtext.spec"