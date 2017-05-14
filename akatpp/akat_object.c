AUTOGLOBAL$() {
    SCOPE$(${object_name}) {
        MAP_IN_SCOPE$(${ns_object_name}, ${object_name});

        IN_GLOBAL$() {
            typedef struct {
                % for m in methods:
                    ${m.ret_type} (* const ${m.name})(${m.args});
                % endfor
            } ${ns_object_name}_t;

            extern ${ns_object_name}_t const ${ns_object_name};
        }

        % for m in methods:
            ${m.body}
        % endfor

        IN_GLOBAL$() {
            SCOPE$(post) {
                ${ns_object_name}_t const ${ns_object_name} = {
                    % for m in methods:
                        .${m.name} = &${m.impl_name}
                        % if not loop.last:
                            ,
                        % endif
                    % endfor
                };
            }
        }
    }
}
