tree alberoABR(char [] s, int n){
  return alberoABRec(s, 1, n, n);

}

tree alberoABRec(char [] s, int i, int j, int n){
  if (i < 1 || j > n){
    return null;
  }
  int mid = i+j /2;
  tree t;
  t.key = s[mid];

  t.left = alberoABRec(s, i, mid - 1, n);
  t.right = alberoABRec(s, mid + 1, j, n);
  t.left.parent = t;
  t.right.parent = t;

  return t;
}
