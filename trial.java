import io.indico.Indico;
import io.indico.api.results.IndicoResult;

public class trial {
  public static void main (String [] args) throws java.io.IOException, io.indico.api.utils.IndicoException {
    
    
    Indico indico = new Indico("9f4ce747d4eab117a262b1c3d5a6ad39");
    IndicoResult single = indico.sentimentHQ.predict(
                                                     "indico is so easy to use!"
                                                    );
    Double result = single.getSentiment();
    System.out.println(result); 
  }
}