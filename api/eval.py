import sys

if __name__ == "__main__":
  try:
    print(eval(sys.argv[1]))
  except:
    print('不正な式です．')