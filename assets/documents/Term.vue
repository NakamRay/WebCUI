<template>
  <div>
    <h3>記法</h3>
      <p>
        ラムダ式中の括弧は自由です．括弧がない場合，ラムダ抽象のλx.MのMをできる限り多くとるようになっています．
        <br><br>
        - 例<br>
        <code>λx:INT.x y</code> → <code>λx:INT.(x y)</code>
      </p>
      <p>
        UntypedスイッチがONとなり，型無しのラムダ式を扱うようになったときは，定数やラムダ抽象の型指定を省略して記述します．
        <br><br>
        - 例<br>
        <code>λx:INT.x y:BOOL</code> → <code>λx.x y</code>
      </p>
    <h3>ユニット</h3>
      <p>
        - 例<br>
        <code>()</code><br><br>
      </p>
    <h3>定数</h3>
      <p>
        任意の定数名に「:（コロン）」を付け，型を指定することで定数として扱われます．
        <br><br>
        - 例<br>
        <code>f:INT->BOOL</code><br><br>
        <code>x:INT</code>
      </p>
    <h3>変数</h3>
      <p>
        任意の小文字の英字から始まる変数名を決められます．
        <br><br>
        - 例<br>
        <code>x</code>
      </p>
    <h3>ラムダ適用</h3>
      <p>
        半角スペースで並べられたラムダ式は，ラムダ適用として扱われます．括弧を省略して並べた場合，左結合します．
        <br><br>
        - 例<br>
        <code>x y</code><br><br>
        <code>x y z</code> → <code>(x y) z</code>
      </p>
    <h3>ラムダ抽象</h3>
      <p>
        ラムダ抽象で束縛される変数は型を持ちます．また，「λ」は「&（アンパサンド）」でも代用できます．
        <br><br>
        - 例<br>
        <code>λx:INT.x</code> or <code>&x:INT.x</code>
      </p>
      <p>
        ラムダ抽象とラムダ式のラムダ適用は，簡約可能な項（Redex）となります．
        <br><br>
        - 例<br>
        <code>(λx:INT.x) a:INT</code>
      </p>
    <h3>タプル</h3>
      <p>
        複数のラムダ式を「,（カンマ）」で区切り，括弧で囲むとタプルとして扱われます．
        <br><br>
        - 例<br>
        <code>(x, y, z)</code>
      </p>
    <h3>プロジェクション</h3>
      <p>
        タプルに「.（ピリオド）」と数字を続けることで，タプルのn番目を取り出す操作となります．
        <br><br>
        - 例<br>
        <code>(x, y, z).3</code> → <code>z</code>
      </p>
    <h3>レコード</h3>
      <p>
        任意のラベルとラムダ式の組を「,（カンマ）」で区切り，波括弧で囲むとレコードとして扱われます．
        <br><br>
        - 例<br>
        <code>{name=s, age: x}</code>
      </p>
    <h3>レコードからの取り出し</h3>
      <p>
        レコードに「.（ピリオド）」とラベルを続けることで，レコードのラベルが一致する値を取り出す操作となります．
        <br><br>
        - 例<br>
        <code>{name=s, age=x}.name</code> → <code>s</code>
      </p>
    <h3>インジェクション</h3>
      <p>
        - 例<br>
        <code>(&lt;name=s&gt;:&lt;name:String, age:Int&gt;)</code>
      </p>
    <h3>ケース文</h3>
      <p>
        - 例<br>
        <code>case (&lt;name=s&gt;:&lt;name:String, age:Int&gt;) of name => λs:String.s, age => λx:Int.x</code> → <code>(λs:String.s) s</code>
      </p>
    <h3>型抽象</h3>
      <p>
        - 例<br>
        <code>ΛT.λx:T.x</code>
      </p>
    <h3>型適用</h3>
      <p>
        - 例<br>
        <code>(ΛT.λx:T.x) INT</code> → <code>λx:INT.x</code>
      </p>
  </div>
</template>
