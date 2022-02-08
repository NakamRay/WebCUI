export const examples = [
  {
    display: 'Typed',
    examples: [
      {
        xi: '',
        ga: 'i:INT',
        term: '(λx:INT.x) ((λx:INT.x) i)',
        isUntyped: false
      },
      {
        xi: '',
        ga: 'a:INT->INT, b:INT',
        term: '(λx:INT->INT.λy:INT.x y) a b',
        isUntyped: false
      },
      {
        xi: '',
        ga: 'a:INT, f:INT->BOOL',
        term: '(λx:INT.f x) ((λx:INT.x) a)',
        isUntyped: false
      },
      {
        xi: '',
        ga: 'y:INT->INT',
        term: '(λx:INT->INT.λy:INT.x y) y',
        isUntyped: false
      },
      {
        xi: '',
        ga: 'x:INT, y:INT, z:INT',
        term: '((λx:INT.(λy:INT.(λz:INT.x) y)) y) z',
        isUntyped: false
      },
      {
        xi: '',
        ga: 'a:INT, b:INT, c:BOOL, f:BOOL->BOOL',
        term: '(λx:BOOL.f x) (a, b, c).3',
        isUntyped: false
      },
      {
        xi: 'String',
        ga: 's:String',
        term: '(λx:String.x) s',
        isUntyped: false
      },
      {
        xi: 'CHAR',
        ga: 'a:INT, b:BOOL, c:CHAR',
        term: '(λx:(INT, BOOL, CHAR).x.3) (a, b, c)',
        isUntyped: false
      },
      {
        xi: '',
        ga: 'a:INT, b:BOOL, f:INT->INT',
        term: '((λx:INT.x) a, (λx:BOOL.x) b, (λx:INT->INT.x) f).2',
        isUntyped: false
      },
      {
        xi: 'String',
        ga: '',
        term: '(ΛX.ΛA.λf:A->X.f) String',
        isUntyped: false
      }
    ]
  },
  {
    display: 'Untyped',
    examples: [
      {
        xi: '',
        ga: '',
        term: '(λx.x x) y',
        isUntyped: true
      },
      {
        xi: '',
        ga: '',
        term: '(λx.x x) (λx.x x)',
        isUntyped: true
      },
      {
        xi: '',
        ga: '',
        term: '(λx.λy.x y) f a',
        isUntyped: true
      },
      {
        xi: '',
        ga: '',
        term: '(λx.λy.x y) ((λx.x) y)',
        isUntyped: true
      },
      {
        xi: '',
        ga: '',
        term: '(λx.λy.λz.x y z) (a, b, c) (d, e, f) (g, h, i)',
        isUntyped: true
      },
      {
        xi: '',
        ga: '',
        term: '(λx.x x) (a, b, c, d, e, (λx.x) f).6',
        isUntyped: true
      }
    ]
  }
]
