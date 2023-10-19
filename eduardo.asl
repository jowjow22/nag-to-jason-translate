estaEnsolarado.
tenhoRedeDeVolei.
tenhoBola.
tenhoProtetorSolar.


!jogarVolei.
!aproveitarDia.


+!jogarVolei: tenhoRedeDeVolei & tenhoBola <-  .printf("sair");
  .printf("montarRede");
  .printf("pegarBola");
  .printf("jogarVolei").
+!aproveitarDia: estaEnsolarado & tenhoProtetorSolar <-  .printf("sair");
  .printf("aplicarProtetorSolar");
  .printf("fazerAtividadesAoArLivre").

