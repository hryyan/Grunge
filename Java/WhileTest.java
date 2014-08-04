/*************************************************************************
	> File Name: WhileTest.java
	> Author: 
	> Mail: 
	> Created Time: 2014年08月03日 星期日 11时39分13秒
 ************************************************************************/
public class WhileTest
{
    static boolean condition()
    {
        boolean result = Math.random() < 0.99;
        System.out.println(result + ", ");
        return result;
    }
    public static void main(String[] args)
    {
        while (condition())
            System.out.println("Inside 'while'");
        System.out.println("Exited 'while'");
   }
}
