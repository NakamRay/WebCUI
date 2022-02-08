const stations = [
  "高崎", "高崎問屋町", "井野", "新前橋", "前橋", "前橋大島", "駒形", "伊勢崎", "国定", "岩宿", "桐生", "小俣", "山前", "足利", "足利フラワーパーク", "富田", "佐野", "岩舟", "大平下", "栃木", "思川", "小山",
  "群馬総社", "八木原", "渋川", "金島", "祖母島", "小野上", "小野上温泉", "市城", "中之条", "群馬原町", "郷原", "矢倉", "岩島", "川原湯温泉", "長野原草津口", "群馬大津", "羽根尾", "袋倉", "万座・鹿沢口", "大前"
]

export const params = {
  from: {
    display: 'From',
    type: 'select',
    items: stations,
    default: '高崎',
    size: 'quarter'
  },
  to: {
    display: 'To',
    type: 'select',
    items: stations,
    default: '前橋',
    size: 'quarter'
  },
  time: {
    display: '出発時刻 (例：0820)',
    type: 'text',
    default: '',
    size: 'half',
    required: true
  }
}
