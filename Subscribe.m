function Subscribe(varargin)
% �������飬���Ż��߷ֺŸ���
inst = '';
if(nargin > 1)
    error('������������С��2');
elseif(nargin == 1)
    inst = varargin{1};
    if(~ischar(inst))
        error('���ĺ�Լ���ʹ���');
    end
end
TraderMain(3, inst);


end
