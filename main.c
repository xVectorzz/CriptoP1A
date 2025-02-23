#include <gtk/gtk.h>
#include <stdio.h>

GtkWidget *radio1, *radio2;
GtkWidget *entry;

int on_button_clicked(GtkWidget *widget, gpointer data) {

    const gchar *text = gtk_entry_get_text(GTK_ENTRY(entry));
    int number = atoi(text);
    const char *filename = "m.txt";
    const char *filenamec = "m_c.txt";
    const char *filenamecr = "m_c_r.txt";
    g_print("Se hara un corrimiento de %i \n", number);
    char character;
    int aux;

    
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio1))) {
        FILE *file = fopen (filename, "r");
        FILE *file2 = fopen (filenamec, "w");

        if(file == NULL){
            perror("Error al abrir la letra de la cancion\n");
            return 1;
        }
        if(file2 == NULL){
            perror("Error al crear el archivo cifrado\n");
            return 1;
        }

        
        while ((character = fgetc(file)) != EOF){
            g_print("Se ha leido la letra %c\n", character);
            aux= (int) character;
            if (aux > 96 && aux < 123 ){
                aux +=number;
                g_print("Se ha escrito la letra %c\n", (char)aux);
                fputc((char)aux, file2);
            }else{
                g_print("Se ha escrito la letra %c\n", (char)aux);
                fputc((char)aux, file2);
            }
        }
        g_print("Se ha completado el corrimiento.\n");


        fclose(file);
        fclose(file2);
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio2))) {
        FILE *file2 = fopen (filenamec, "r");
        FILE *file3 = fopen (filenamecr, "w");

        if(file2 == NULL){
            perror("Error al abrir la letra de la cancion\n");
            return 1;
        }
        if(file3 == NULL){
            perror("Error al crear el archivo cifrado\n");
            return 1;
        }
        while ((character = fgetc(file2)) != EOF){
            aux= (int) character;
            if((aux > 97 && aux < 148 )){
                g_print("Se ha leido la letra %c\n", character);
                aux -=number;
                g_print("Se ha escrito la letra %c\n", (char)aux);
                fputc((char)aux, file3);

                
            }else {
                g_print("Se ha leido un caracter especial");
                fputc((char)aux, file3);
            }
            

        }
        fclose(file2);
        fclose(file3);
        
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Ejercicio 1 Programa A");
    gtk_container_set_border_width(GTK_CONTAINER(window), 100);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    
    radio1 = gtk_radio_button_new_with_label(NULL, "Encriptar");
    gtk_box_pack_start(GTK_BOX(vbox), radio1, FALSE, FALSE, 0);
    
    radio2 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio1), "Desencriptar");
    gtk_box_pack_start(GTK_BOX(vbox), radio2, FALSE, FALSE, 0);

    entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Ingrese un número");  // Texto de ayuda
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);
    
    GtkWidget *button = gtk_button_new_with_label("Confirmar");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);
    
    gtk_widget_show_all(window);
    gtk_main();
    
    return 0;
}
