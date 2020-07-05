function append_value(file, name, value)
     dlmwrite(file, ['Start_' name], 'delimiter', '', '-append');
     dlmwrite(file, value, 'delimiter', '\t', 'precision', 16, '-append');
     dlmwrite(file, ['End_' name], 'delimiter', '', '-append');
end