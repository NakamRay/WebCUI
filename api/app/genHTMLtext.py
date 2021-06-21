import sys

if __name__ == "__main__":
  try:
    msg    = sys.argv[1]
    pre    = sys.argv[2]
    suf    = sys.argv[3]
    enable = sys.argv[4]
    isDeco = sys.argv[5]
    color  = sys.argv[6]
    isBold = sys.argv[7]
    isUL   = sys.argv[8]

    prefix     = ""
    suffix     = ""
    deco_start = ""
    deco_end   = ""

    if enable == "ps":
      prefix = pre
      suffix = suf
    elif enable == "p":
      prefix = pre
    elif enable == "s":
      suffix = suf
    

    if isDeco == "true":
      if color == "red":
        deco_start = "<font class=\"red--text\">" + deco_start
        deco_end   = deco_end + "</font>"
      if color == "green":
        deco_start = "<font class=\"green--text\">" + deco_start
        deco_end   = deco_end + "</font>"
      if color == "blue":
        deco_start = "<font class=\"blue--text\">" + deco_start
        deco_end   = deco_end + "</font>"
      if isBold == "true":
        deco_start = "<b>" + deco_start
        deco_end   = deco_end + "</b>"
      if isUL == "true":
        deco_start = "<u>" + deco_start
        deco_end   = deco_end + "</u>"

    print(deco_start + prefix + msg + suffix + deco_end)
  except:
    print("Error")
