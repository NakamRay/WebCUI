<template>
  <div>
    <h3>型チェック</h3>
      <p>
        簡約を開始する前に入力された式の型規則をチェックします．
        型規則が正しくない場合，Typing Errorと表示され，簡約が開始されません．
      </p>
    <h3>種類</h3>
      <p>
        <i>Type</i> ::= Unit | INT | BOOL <br>
        | <i>Type</i> -><i>Type</i> | (<i>Type</i>,..., <i>Type</i>) | {l:<i>Type</i>,..., l:<i>Type</i>} | &lt;l:<i>Type</i>,..., l:<i>Type</i>&gt; <br>
        | T | ∀T.<i>Type</i>
      </p>
    <h3>記法</h3>
      <p>
        Type Contextは，自由型変数の名前を「，（カンマ）」で区切って表現します．
        自由型変数を含まない式で，型環境を指定する必要がない場合は，空欄のまま入力することができます．
        変数名は大文字の英字から始まるようにします．
        <br><br>
        - 例<br>
        <code>String, Long</code>
      </p>
      <p>
        Term Contextは，自由変数の名前に「：（コロン）」とその型を指定したものを「，（カンマ）」で区切って並べて表現します．
        自由変数を含まない式で，型環境を指定する必要がない場合は，空欄のまま入力することができます．
        変数名は小文字の英字から始まるようにします．
        <br><br>
        - 例<br>
        <code>a:INT, b:BOOL, f:INT->BOOL</code>
      </p>
    <!-- <h3>型規則</h3>
      <p>
        各ラムダ項に対する型規則を以下に示します．Typeは型を，Mはラムダ式を表しています．
        また，[]括弧に囲まれた部分は，型環境の下で正しいとします．
        <br><br>
        - 定数<br>
        <code>c:Type</code>
        <br><br>
        - 変数<br>
        <code>x:Type (xは束縛変数 または 型環境で型を定義済みの自由変数)</code>
        <br><br>
        - ラムダ適用<br>
        <code>M1 M2:Type2 [M1:Type1->Type2, M2:Type1]</code>
        <br><br>
        - ラムダ抽象<br>
        <code>λx.M:Type1->Type2 [x:Type1, M:Type2]</code>
        <br><br>
        - タプル<br>
        <code>(M1,...,Mn):(Type1,...,Typen) [Mi:Typei (1≦i≦n)]</code>
        <br><br>
        - プロジェクション<br>
        <code>M.i:Typei [M:(M1,...,Mn)] (1≦i≦n)</code>
      </p> -->
  </div>
</template>
